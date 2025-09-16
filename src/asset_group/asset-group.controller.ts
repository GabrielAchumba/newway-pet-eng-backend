import { Controller, Get, Post, Body, Param, Delete, Put, ParseIntPipe } from '@nestjs/common';
import { AssetGroupService } from './asset_group_service';
import { CreateAssetGroupDto } from './dto/create-asset-group.dto';
import { UpdateAssetGroupDto } from './dto/update-asset-group.dto';

@Controller('asset-groups')
export class AssetGroupController {
  constructor(private readonly assetGroupService: AssetGroupService) {}

  @Post()
  create(@Body() dto: CreateAssetGroupDto) {
    console.log("dto: ", dto);
    return this.assetGroupService.create(dto);
  }

  @Get()
  findAll() {
    return this.assetGroupService.findAll();
  }

  @Get(':id')
  findOne(@Param('id', ParseIntPipe) id: number) {
    return this.assetGroupService.findOne(id);
  }

  @Put(':id')
  update(@Param('id', ParseIntPipe) id: number, @Body() dto: UpdateAssetGroupDto) {
    return this.assetGroupService.update(id, dto);
  }

  @Delete(':id')
  remove(@Param('id', ParseIntPipe) id: number) {
    return this.assetGroupService.remove(id);
  }
}