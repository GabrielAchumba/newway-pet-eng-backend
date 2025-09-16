import {
  Controller, Post, Req, Query, Res, Sse, Get
} from '@nestjs/common';
import { Request, Response } from 'express';
import { ExcelService } from './excel.service';
import { Observable } from 'rxjs';

@Controller('excel')
export class ExcelController {
  constructor(private readonly excel: ExcelService) {}

  // Ingest NDJSON: each line is a JSON with {type:'rows', rows:[...], source:string}
  @Post('ingest')
  async ingest(
    @Req() req: Request,
    @Res() res: Response,
    @Query('sheet') sheet: string,
  ) {
    res.setHeader('Content-Type', 'text/plain; charset=utf-8');

    try {
      await this.excel.consumeNdjson(req, sheet, (progress) => {
        // Optionally write lightweight acks (not SSE) just to keep connection healthy
        // res.write(JSON.stringify({ok:true, progress}) + '\n');
      });

      res.status(200).end('OK\n');
    } catch (e: any) {
      res.status(500).end(String(e?.message || e));
    }
  }

  // Optional: SSE progress channel
  @Sse('progress')
  progress(): Observable<MessageEvent> {
    return this.excel.progress$ as unknown as Observable<MessageEvent>;
  }
}