import {
    Injectable,
    NotFoundException,
} from '@nestjs/common';
import { CreateFieldDto } from './dto/create_field_dto';
import { UpdateFieldDto } from './dto/update_field_dto';
import { DatabaseService } from 'src/database/database.service';
import { IAsset, TAsset } from './dto/create_assets_dto';
  
@Injectable()
export class  FieldService {
constructor(
    private readonly prisma: DatabaseService,
) {}

    async create(data: CreateFieldDto) {
        console.log("data: ", data);
        try {
            return await this.prisma.field.create({ data });
        } catch (error) {
            console.log(error)
            return error;
        }
    }

    async createMany(data: TAsset, assetGroupId: number) {
        console.log("data: ", data);

            let fieldsDto = data.map((row:IAsset) => {
                return {
                    name: row.name,
                    description: row.description,
                    AssetGroupId: assetGroupId,
                } as any
            });

        try {
            const existingFields =  await this.findAll();
            let nonExistingFields = [] as CreateFieldDto[];

            for(const item of fieldsDto){
                let field = existingFields.find(_field => _field.name == item.name) as CreateFieldDto;
                let newField = nonExistingFields.find(nonExistingField => nonExistingField.name == item.name) as CreateFieldDto;

                if(!field && !newField){
                    nonExistingFields.push(item as CreateFieldDto);
                }

            }
            
            return this.prisma.field.createMany({ data: nonExistingFields }); // Error can only occur if nonExistingFields is empty
            
        } catch (error) {
            console.log(error)
            return error;
        }
    }

    async findAll() {
        return await this.prisma.field.findMany();
    }

    async findOne(id: number) {
        const  Field = await this.prisma. field.findUnique({ where: { id } });
        if (! Field) throw new NotFoundException(` Field #${id} not found`);
        return  Field;
    }

    async update(id: number, data: UpdateFieldDto) {
        await this.findOne(id); // ensure exists
        return this.prisma.field.update({
        where: { id },
        data,
        });
    }

    async remove(id: number) {
        await this.findOne(id); // ensure exists
        return this.prisma.field.delete({ where: { id } });
    }
      
}