import {
    Injectable,
    NotFoundException,
} from '@nestjs/common';
import { CreateAssetGroupDto } from './dto/create-asset-group.dto';
import { UpdateAssetGroupDto } from './dto/update-asset-group.dto';
import { DatabaseService } from 'src/database/database.service';
  
@Injectable()
export class AssetGroupService {
constructor(
    private readonly prisma: DatabaseService,
) {}

    create(data: CreateAssetGroupDto) {
        return this.prisma.assetGroup.create({ data });
    }

    findAll() {
        return this.prisma.assetGroup.findMany();
    }

    async findOne(id: number) {
        const assetGroup = await this.prisma.assetGroup.findUnique({ where: { id } });
        if (!assetGroup) throw new NotFoundException(`AssetGroup #${id} not found`);
        return assetGroup;
    }

    async update(id: number, data: UpdateAssetGroupDto) {
        await this.findOne(id); // ensure exists
        return this.prisma.assetGroup.update({
        where: { id },
        data,
        });
    }

    async remove(id: number) {
        await this.findOne(id); // ensure exists
        return this.prisma.assetGroup.delete({ where: { id } });
    }
      
}