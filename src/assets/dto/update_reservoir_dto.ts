import { PartialType } from '@nestjs/mapped-types';
import { CreateReservoirDto } from './create_reservoir_dto';

export class UpdateReservoirDto extends PartialType(CreateReservoirDto) {}