import {
    Injectable,
    NotFoundException,
} from '@nestjs/common';
import { CreateWellDto } from './dto/create_well_dto';
import { UpdateWellDto } from './dto/update_well_dto';
import { DatabaseService } from 'src/database/database.service';
import { IAsset, TAsset } from './dto/create_assets_dto';
import { FieldService } from './field_service'; 
  
@Injectable()
export class  WellService {
constructor(
    private readonly prisma: DatabaseService,
    private readonly fieldService: FieldService,
) {}

    create(data: CreateWellDto) {
        console.log("data: ", data);
        try {
            return this.prisma.well.create({ data });
        } catch (error) {
            console.log(error)
            return error;
        }
    }

    createWellStrings(wellList: TAsset, 
        stringList: TAsset, wellStringList: TAsset, fieldList: TAsset, assetGroupId: number) {
        console.log("wellList: ", wellList);

        let wellsDto = [] as any[];

        if(wellList.length > 0 && stringList.length > 0){
            wellsDto = wellList.map((row:IAsset, idx:number) => {
                return {
                    name: row.name,
                    description: row.description,
                    AssetGroupId: assetGroupId,
                    fieldName: fieldList[idx].name,
                    isWellTogether: false,
                    productionString: stringList[idx].name,
                } as any
            });
        }else{
            wellsDto = wellStringList.map((row:IAsset, idx:number) => {
                return {
                    name: row.name,
                    description: row.description,
                    AssetGroupId: assetGroupId,
                    fieldName: fieldList[idx].name,
                    isWellTogether: true,
                    productionString: "",
                } as any
            });
        }

        return wellsDto;
    }
        
        
    async createMany(wellsDto: any[]) {
        console.log("wellsDto: ", wellsDto);

        try {
            const existingWells =  await this.findAll();
            const existingFields = await this.fieldService.findAll();

            let nonExistingWells = [] as any[];

            for(const item of wellsDto){

                let field = existingFields.find(_field => _field.name == item.fieldName);

                let well = existingWells.find(_reservoir => _reservoir.name == item.name) as CreateWellDto;

                let newWell = nonExistingWells.find(nonExistingWell => nonExistingWell.name == item.name);

                if(!well && !newWell && field){
                    nonExistingWells.push({
                        ...item,
                        FieldId: field.id,
                    } as any);
                }

            }
            
            const reqBody = nonExistingWells.map((row) => {
                return {
                    name: row.name,
                    description: row.description,
                    AssetGroupId: row.AssetGroupId,
                    FieldId: row.FieldId,
                    isWellTogether: row.isWellTogether,
                    productionString: row.productionString,
                } as CreateWellDto;
            });

            return this.prisma.well.createMany({ data: reqBody }); // Error can only occur if nonExistingWells is empty
            
        } catch (error) {
            console.log(error)
            return error;
        }
    }

    findAll() {
        return this.prisma.well.findMany();
    }

    async findOne(id: number) {
        const  Well = await this.prisma.well.findUnique({ where: { id } });
        if (! Well) throw new NotFoundException(` Well #${id} not found`);
        return  Well;
    }

    async update(id: number, data: UpdateWellDto) {
        await this.findOne(id); // ensure exists
        return this.prisma.well.update({
        where: { id },
        data,
        });
    }

    async remove(id: number) {
        await this.findOne(id); // ensure exists
        return this.prisma.well.delete({ where: { id } });
    }
      
}