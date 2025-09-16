import { IsString, Length } from 'class-validator';

export class CreateReservoirDto {
  @IsString()
  @Length(3, 100)
  name: string;

  @IsString()
  description: string;

  AssetGroupId: number;
  FieldId: number;
}