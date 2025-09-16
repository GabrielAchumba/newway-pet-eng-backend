import { PartialType } from '@nestjs/mapped-types';
import { CreateWellDto } from './create_well_dto';

export class UpdateWellDto extends PartialType(CreateWellDto) {}