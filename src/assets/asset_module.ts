import { Module } from '@nestjs/common';
import { AssetService } from './asset_service';
import { AssetController } from './asset_controller';
import { FileWriterService } from '../utils/file_writer_service';
import { FieldService } from './field_service'; 
import { ReservoirService } from './reservoir_service';
import { WellService } from './well_service';
import { DrainagePointService } from './drainage_point_service';

@Module({
  controllers: [
    AssetController
],
  providers: [
    AssetService, 
    FileWriterService, 
    FieldService,
    ReservoirService,
    WellService,
    DrainagePointService
],
  exports: [
    AssetService, 
    FieldService,
    ReservoirService,
    WellService,
    DrainagePointService
],
})
export class AssetModule {}