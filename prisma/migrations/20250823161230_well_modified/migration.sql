/*
  Warnings:

  - Added the required column `isWellTogether` to the `Well` table without a default value. This is not possible if the table is not empty.
  - Added the required column `productionString` to the `Well` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE `well` ADD COLUMN `isWellTogether` BOOLEAN NOT NULL,
    ADD COLUMN `productionString` VARCHAR(191) NOT NULL;
