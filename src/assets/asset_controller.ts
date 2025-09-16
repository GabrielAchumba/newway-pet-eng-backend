import { Controller, Get, Post, Body, Param, Delete, Put, ParseIntPipe } from '@nestjs/common';
import { AssetService } from './asset_service';
import { CreateAssetsDto } from './dto/create_assets_dto';

@Controller('assets')
export class AssetController {
  constructor(private readonly assetService: AssetService) {}

  @Post()
  create(@Body() dto: CreateAssetsDto) {
    console.log("dto: ", dto);
    return this.assetService.create(dto);
  }
}