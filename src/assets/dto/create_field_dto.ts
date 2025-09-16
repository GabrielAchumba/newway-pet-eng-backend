import { IsString, Length } from 'class-validator';

export class CreateFieldDto {
  @IsString()
  @Length(3, 100)
  name: string;

  @IsString()
  description: string;

  AssetGroupId: number;
}