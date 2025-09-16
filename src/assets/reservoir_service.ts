import {
    Injectable,
    NotFoundException,
} from '@nestjs/common';
import { CreateReservoirDto } from './dto/create_reservoir_dto';
import { UpdateReservoirDto } from './dto/update_reservoir_dto';
import { DatabaseService } from 'src/database/database.service';
import { IAsset, TAsset } from './dto/create_assets_dto';
import { FieldService } from './field_service'; 
  
@Injectable()
export class  ReservoirService {
constructor(
    private readonly prisma: DatabaseService,
    private readonly fieldService: FieldService,
) {}

    create(data: CreateReservoirDto) {
        console.log("data: ", data);
        try {
            return this.prisma.reservoir.create({ data });
        } catch (error) {
            console.log(error)
            return error;
        }
    }
    
    
    async createMany(data: TAsset, fieldList: TAsset, assetGroupId: number) {
        console.log("data: ", data);

            let resevoirsDto = data.map((row:IAsset, idx:number) => {
                return {
                    name: row.name,
                    description: row.description,
                    AssetGroupId: assetGroupId,
                    fieldName: fieldList[idx].name,
                } as any
            });

        try {
            const existingReserviors =  await this.findAll();
            const existingFields = await this.fieldService.findAll();

            let nonExistingReservoirs = [] as CreateReservoirDto[];

            for(const item of resevoirsDto){

                let field = existingFields.find(_field => _field.name == item.fieldName);

                let reservoir = existingReserviors.find(_reservoir => _reservoir.name == item.name) as CreateReservoirDto;
                let newReservoir = nonExistingReservoirs.find(nonExistingReservoir => nonExistingReservoir.name == item.name) as CreateReservoirDto;

                if(!reservoir && !newReservoir && field){
                    nonExistingReservoirs.push({
                        ...item,
                        FieldId: field.id
                    } as CreateReservoirDto);
                }

            }

            const reqBody = nonExistingReservoirs.map((row) => {
                return {
                    name: row.name,
                    description: row.description,
                    AssetGroupId: assetGroupId,
                    FieldId: row.FieldId
                } as CreateReservoirDto
            });
            
            return this.prisma.reservoir.createMany({ data:  reqBody}); // Error can only occur if nonExistingReservoirs is empty
            
        } catch (error) {
            console.log(error)
            return error;
        }
    }

    findAll() {
        return this.prisma.reservoir.findMany();
    }

    async findOne(id: number) {
        const  Reservoir = await this.prisma.reservoir.findUnique({ where: { id } });
        if (! Reservoir) throw new NotFoundException(` Reservoir #${id} not found`);
        return  Reservoir;
    }

    async update(id: number, data: UpdateReservoirDto) {
        await this.findOne(id); // ensure exists
        return this.prisma.reservoir.update({
        where: { id },
        data,
        });
    }

    async remove(id: number) {
        await this.findOne(id); // ensure exists
        return this.prisma.reservoir.delete({ where: { id } });
    }
      
}