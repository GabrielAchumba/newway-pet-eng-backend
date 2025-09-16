import { IsString, Length } from 'class-validator';

export class CreateWellDto {
  @IsString()
  @Length(3, 100)
  name: string;

  @IsString()
  description: string;

  AssetGroupId: number;
  FieldId: number;

  isWellTogether: boolean;

  @IsString()
  productionString: string; 
}