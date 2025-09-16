import { Injectable, Logger } from '@nestjs/common';
import { Subject } from 'rxjs';

type RowsEvent = { type: 'rows'; rows: any[]; source?: string };
type FileEndEvent = { type: 'file_end'; source?: string };
type EndEvent = { type: 'end' };
type ErrorEvent = { type: 'error'; message: string; source?: string };
type AnyEvent = RowsEvent | FileEndEvent | EndEvent | ErrorEvent;

@Injectable()
export class ExcelService {
  private readonly logger = new Logger(ExcelService.name);
  private _progress$ = new Subject<{ type: string; message?: string; count?: number }>();
  public get progress$() { return this._progress$.asObservable(); }

  private totalRows = 0;

  /**
   * Consume an NDJSON stream line-by-line.
   * For each {type:'rows', rows:[...]} event, persist to DB in bulk.
   */
  async consumeNdjson(req: any, sheet: string, onAck?: (p: any) => void): Promise<void> {
    this.logger.log(`Start ingest for sheet="${sheet}"`);
    let buffer = Buffer.alloc(0);

    const writeBatch = async (rows: any[]) => {
      if (!rows?.length) return;
      // TODO: replace with your DB bulk insert
      // await this.repo.insertMany(rows)
      this.totalRows += rows.length;
      this._progress$.next({ type: 'rows', count: this.totalRows });
      onAck?.({ rows: this.totalRows });
    };

    await new Promise<void>((resolve, reject) => {
      req.on('data', async (chunk: Buffer) => {
        buffer = Buffer.concat([buffer, chunk]);
        // Split by newline
        let idx: number;
        while ((idx = buffer.indexOf(0x0a)) !== -1) { // '\n'
          const line = buffer.subarray(0, idx).toString('utf8').trim();
          buffer = buffer.subarray(idx + 1);
          if (!line) continue;

          try {
            const evt: AnyEvent = JSON.parse(line);
            if (evt.type === 'rows') {
              await writeBatch(evt.rows);
            } else if (evt.type === 'file_end') {
              this._progress$.next({ type: 'file_end', message: evt.source });
            } else if (evt.type === 'error') {
              this.logger.warn(`Client error from ${evt.source}: ${evt.message}`);
              this._progress$.next({ type: 'client_error', message: evt.message });
            } else if (evt.type === 'end') {
              resolve();
            }
          } catch (e: any) {
            this.logger.error(`Bad NDJSON line: ${e?.message || e}`);
          }
        }
      });

      req.on('end', () => resolve());
      req.on('error', (e: any) => reject(e));
      req.on('close', () => resolve());
    });

    this.logger.log(`Ingest complete. totalRows=${this.totalRows}`);
    this._progress$.next({ type: 'end', count: this.totalRows });
  }
}