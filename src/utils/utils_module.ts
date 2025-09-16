import { Module } from '@nestjs/common';
import { FileWriterService } from './file_writer_service';

@Module({
  providers: [FileWriterService],
  exports: [FileWriterService],
})
export class UtilsModule {}
