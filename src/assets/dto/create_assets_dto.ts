import { IsOptional, IsNumber } from 'class-validator';

export interface IAsset {
  name: string;
  description: string;  
}


export type TAsset = IAsset[];

export class CreateAssetsDto {

  @IsOptional()  
  wells: TAsset;

  @IsOptional() 
  reservoirs: TAsset;

  @IsOptional() 
  fields: TAsset;

  @IsOptional() 
  productionStrings: TAsset;

  @IsOptional() 
  wellProductionStrings: TAsset;

  @IsNumber()
  AssetGroupId: number;
}