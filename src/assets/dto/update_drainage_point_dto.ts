import { PartialType } from '@nestjs/mapped-types';
import { CreateDrainagePointDto } from './create_drainage_point_dto';

export class UpdateDrainagePointDto extends PartialType(CreateDrainagePointDto) {}