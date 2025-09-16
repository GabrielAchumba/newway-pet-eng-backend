import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { DatabaseModule } from "./database/database.module";
import { AssetGroupModule } from "./asset_group/asset-group.module";
import { UtilsModule } from "./utils/utils_module";
import { AssetModule } from "./assets/asset_module";
import { ExcelModule } from "./data_streaming/excel.module";

@Module({
  imports: [
    DatabaseModule, 
    UtilsModule, 
    ExcelModule,
    AssetGroupModule,
    AssetModule
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
