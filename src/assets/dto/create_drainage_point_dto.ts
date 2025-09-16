import { IsString, Length } from 'class-validator';

export class CreateDrainagePointDto {
  @IsString()
  @Length(3, 100)
  name: string;

  @IsString()
  description: string;

  AssetGroupId: number;
  ReservoirId: number;
  FieldId: number;
}