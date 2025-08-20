import { Module } from '@nestjs/common';
import { AssetGroupService } from './asset_group_service';
import { AssetGroupController } from './asset-group.controller';

@Module({
  controllers: [AssetGroupController],
  providers: [AssetGroupService],
  exports: [AssetGroupService],
})
export class AssetGroupModule {}