/*
  Warnings:

  - Added the required column `FieldId` to the `DrainagePoint` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE `drainagepoint` ADD COLUMN `FieldId` INTEGER NOT NULL;
