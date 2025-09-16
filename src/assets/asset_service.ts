import {
    Injectable,
    NotFoundException,
} from '@nestjs/common';
import { CreateAssetsDto, IAsset } from './dto/create_assets_dto';
import { DatabaseService } from 'src/database/database.service';
import { FileWriterService } from 'src/utils/file_writer_service';
import { FieldService } from './field_service'; 
import { ReservoirService } from './reservoir_service';
import { WellService } from './well_service';
import { DrainagePointService } from './drainage_point_service';
import { CreateFieldDto } from './dto/create_field_dto';
  
@Injectable()
export class AssetService {
constructor(
    private readonly prisma: DatabaseService,
    private readonly fileWriterService: FileWriterService,
    private readonly fieldService: FieldService,
    private readonly reservoirService: ReservoirService,
    private readonly wellService: WellService,
    private readonly drainagePointService: DrainagePointService,
) {}

    async create(data: CreateAssetsDto) {
        try {
            
            const fieldsResponse = await this.fieldService.createMany(data.fields, data.AssetGroupId);

            const reservoirResponse = await this.reservoirService.createMany(data.reservoirs, data.fields, 
                data.AssetGroupId);

            const wellStrings = this.wellService.createWellStrings(data.wells, data.productionStrings, 
                data.wellProductionStrings,
                data.fields, data.AssetGroupId);

            const wellResponse = await this.wellService.createMany(wellStrings);

            const drainageResponse = await this.drainagePointService.createMany(wellStrings, data.fields, 
                data.reservoirs, data.AssetGroupId);

            //wellsDto: any[], fieldList: TAsset, reservoirList: TAsset, assetGroupId: number
            // const payload = {
            //     payload: { ... data }
            // }
            // await this.fileWriterService.writeToFile(payload, "data/assets/subsurface_assets.json")
            return data;

        } catch (error) {

            return error;
        }
    }
      
}