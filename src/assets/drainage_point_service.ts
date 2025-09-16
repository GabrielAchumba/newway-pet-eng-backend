import {
    Injectable,
    NotFoundException,
} from '@nestjs/common';
import { CreateDrainagePointDto } from './dto/create_drainage_point_dto';
import { UpdateDrainagePointDto } from './dto/update_drainage_point_dto';
import { DatabaseService } from 'src/database/database.service';
import { FieldService } from './field_service'; 
import { ReservoirService } from './reservoir_service';
import { TAsset } from './dto/create_assets_dto';
  
@Injectable()
export class  DrainagePointService {
constructor(
    private readonly prisma: DatabaseService,
    private readonly fieldService: FieldService,
    private readonly reservoirService: ReservoirService,
) {}

    create(data: CreateDrainagePointDto) {
        console.log("data: ", data);
        try {
            return this.prisma.drainagePoint.create({ data });
        } catch (error) {
            console.log(error)
            return error;
        }
    }            
            
    async createMany(wellsDto: any[], fieldList: TAsset, reservoirList: TAsset, assetGroupId: number) {

        console.log("wellsDto: ", wellsDto);

        const drainagePointList = wellsDto.map((row:any, idx:number) => {

            const wellString = wellsDto[idx].isWellTogether == true ? 
            wellsDto[idx].name : `${wellsDto[idx].name}${wellsDto[idx].productionString}`;
            
            return {
                name: `${fieldList[idx].name}_${wellString}_${reservoirList[idx].name}`,
                description: `${fieldList[idx].name}_${wellString}_${reservoirList[idx].name}`,
                AssetGroupId: assetGroupId,
                fieldName: fieldList[idx].name,
                reservoirName: reservoirList[idx].name
            }
        })

        try {
            const existingDrainagePoints =  await this.findAll();
            const existingFields = await this.fieldService.findAll();
            const existingReservoirs = await this.reservoirService.findAll();

            let nonExistingDrainagePoints = [] as any[];

            for(const item of drainagePointList){

                let field = existingFields.find(_field => _field.name == item.fieldName);

                let reservoir = existingReservoirs.find(_reservoir => _reservoir.name == item.reservoirName);

                let drainagePoint = existingDrainagePoints.find(_drainagePoint => _drainagePoint.name == item.name) as any;

                let newDrainagePoint = nonExistingDrainagePoints.find(nonExistingDrainagePoint => nonExistingDrainagePoint.name == item.name);

                if(!drainagePoint && !newDrainagePoint && field && reservoir){
                    nonExistingDrainagePoints.push({
                        ...item,
                        ReservoirId: reservoir.id,
                        FieldId: field.id,
                    } as any);
                }

            }

            const reqBody = nonExistingDrainagePoints.map((row) => {
                return {
                    name: row.name,
                    description: row.description,
                    AssetGroupId: row.AssetGroupId,
                    FieldId: row.FieldId,
                    ReservoirId: row.ReservoirId,
                } as CreateDrainagePointDto;
            })
            
            return this.prisma.drainagePoint.createMany({ data: reqBody }); // Error can only occur if nonExistingDrainagePoints is empty
            
        } catch (error) {
            console.log(error)
            return error;
        }
    }

    findAll() {
        return this.prisma.drainagePoint.findMany();
    }

    async findOne(id: number) {
        const  DrainagePoint = await this.prisma.drainagePoint.findUnique({ where: { id } });
        if (! DrainagePoint) throw new NotFoundException(` DrainagePoint #${id} not found`);
        return  DrainagePoint;
    }

    async update(id: number, data: UpdateDrainagePointDto) {
        await this.findOne(id); // ensure exists
        return this.prisma.drainagePoint.update({
        where: { id },
        data,
        });
    }

    async remove(id: number) {
        await this.findOne(id); // ensure exists
        return this.prisma.drainagePoint.delete({ where: { id } });
    }
      
}