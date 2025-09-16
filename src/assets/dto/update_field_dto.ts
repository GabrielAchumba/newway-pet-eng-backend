import { PartialType } from '@nestjs/mapped-types';
import { CreateFieldDto } from './create_field_dto';

export class UpdateFieldDto extends PartialType(CreateFieldDto) {}