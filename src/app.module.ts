import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { DatabaseModule } from "./database/database.module";
import { AssetGroupModule } from "./asset_group/asset-group.module";
@Module({
  imports: [DatabaseModule, AssetGroupModule],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
