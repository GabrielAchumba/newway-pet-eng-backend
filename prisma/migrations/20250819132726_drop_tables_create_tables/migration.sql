/*
  Warnings:

  - You are about to drop the `account` table. If the table is not empty, all the data it contains will be lost.
  - You are about to drop the `customer` table. If the table is not empty, all the data it contains will be lost.

*/
-- DropForeignKey
ALTER TABLE `account` DROP FOREIGN KEY `Account_customerId_fkey`;

-- DropTable
DROP TABLE `account`;

-- DropTable
DROP TABLE `customer`;

-- CreateTable
CREATE TABLE `Production` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `DrainagePointId` INTEGER NOT NULL,
    `AssetGroupId` INTEGER NOT NULL,
    `Lease` VARCHAR(191) NOT NULL,
    `FacilityName` VARCHAR(191) NOT NULL,
    `Field` VARCHAR(191) NOT NULL,
    `Reservoir` VARCHAR(191) NOT NULL,
    `TubingString` VARCHAR(191) NOT NULL,
    `DrainagePoint` VARCHAR(191) NOT NULL,
    `Date2` VARCHAR(191) NOT NULL,
    `SplitFactor` DOUBLE NOT NULL,
    `OilProduced` DOUBLE NOT NULL,
    `GasProduced` DOUBLE NOT NULL,
    `WaterProduced` DOUBLE NOT NULL,
    `GasInjected` DOUBLE NOT NULL,
    `WaterInjected` DOUBLE NOT NULL,
    `LiquidProduced` DOUBLE NOT NULL,
    `OilProdDaysRate` DOUBLE NOT NULL,
    `GasProdDaysRate` DOUBLE NOT NULL,
    `WaterProdDaysRate` DOUBLE NOT NULL,
    `LiquidProdDaysRate` DOUBLE NOT NULL,
    `GasInjectionProdDaysRate` DOUBLE NOT NULL,
    `WaterInjectionProdDaysRate` DOUBLE NOT NULL,
    `OilCalendarDaysRate` DOUBLE NOT NULL,
    `GasCalendarDaysRate` DOUBLE NOT NULL,
    `WaterCalendarDaysRate` DOUBLE NOT NULL,
    `LiquidCalendarDaysRate` DOUBLE NOT NULL,
    `GasInjectionCalendarDaysRate` DOUBLE NOT NULL,
    `WaterInjectionCalendarDaysRate` DOUBLE NOT NULL,
    `ProdHours` DOUBLE NOT NULL,
    `ProdDays` DOUBLE NOT NULL,
    `DefermentFactor` DOUBLE NOT NULL,
    `CumulativeOilProduced` DOUBLE NOT NULL,
    `CumulativeGasProduced` DOUBLE NOT NULL,
    `CumulativeWaterProduced` DOUBLE NOT NULL,
    `CumulativeWaterInjected` DOUBLE NOT NULL,
    `CumulativeGasInjected` DOUBLE NOT NULL,
    `CumulativeLiquidProduced` DOUBLE NOT NULL,
    `UltimateRecovery` DOUBLE NOT NULL,
    `WaterCut` DOUBLE NOT NULL,
    `ProdGOR` DOUBLE NOT NULL,
    `WaterGasRatio` DOUBLE NOT NULL,
    `CondensateGasRatio` DOUBLE NOT NULL,
    `ProdTHP` DOUBLE NOT NULL,
    `ProdBean` DOUBLE NOT NULL,
    `ProdSand` DOUBLE NOT NULL,
    `ReservoirPressure` DOUBLE NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- CreateTable
CREATE TABLE `WellTest` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `DrainagePointId` INTEGER NOT NULL,
    `AssetGroupId` INTEGER NOT NULL,
    `Lease` VARCHAR(191) NOT NULL,
    `FacilityName` VARCHAR(191) NOT NULL,
    `Field` VARCHAR(191) NOT NULL,
    `Reservoir` VARCHAR(191) NOT NULL,
    `TubingString` VARCHAR(191) NOT NULL,
    `DrainagePoint` VARCHAR(191) NOT NULL,
    `Facility` VARCHAR(191) NOT NULL,
    `Date1` DATETIME(3) NOT NULL,
    `ChokeSize` DOUBLE NOT NULL,
    `THPNew` DOUBLE NOT NULL,
    `WellHeadTemperature` DOUBLE NOT NULL,
    `FlowLineTemperature` DOUBLE NOT NULL,
    `FlowLinePressure` DOUBLE NOT NULL,
    `ManifoldPressure` DOUBLE NOT NULL,
    `SeparatorPressure` DOUBLE NOT NULL,
    `SeparatorTemperature` DOUBLE NOT NULL,
    `CasingHeadPressure` DOUBLE NOT NULL,
    `LiquidNew` DOUBLE NOT NULL,
    `GasNew` DOUBLE NOT NULL,
    `OilNew` DOUBLE NOT NULL,
    `WaterNew` DOUBLE NOT NULL,
    `WaterCut` DOUBLE NOT NULL,
    `ProdGOR` DOUBLE NOT NULL,
    `CondensateGasRatio` DOUBLE NOT NULL,
    `WaterGasRatio` DOUBLE NOT NULL,
    `DailyLiquidVolume` DOUBLE NOT NULL,
    `ProdDays` DOUBLE NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- CreateTable
CREATE TABLE `DrainagePoint` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `AssetGroupId` INTEGER NOT NULL,
    `ReservoirId` INTEGER NOT NULL,
    `name` VARCHAR(191) NOT NULL,
    `description` VARCHAR(191) NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    UNIQUE INDEX `DrainagePoint_name_key`(`name`),
    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- CreateTable
CREATE TABLE `Facility` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(191) NOT NULL,
    `AssetGroupId` INTEGER NOT NULL,
    `description` VARCHAR(191) NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    UNIQUE INDEX `Facility_name_key`(`name`),
    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- CreateTable
CREATE TABLE `Field` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(191) NOT NULL,
    `AssetGroupId` INTEGER NOT NULL,
    `description` VARCHAR(191) NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    UNIQUE INDEX `Field_name_key`(`name`),
    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- CreateTable
CREATE TABLE `Reservoir` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(191) NOT NULL,
    `AssetGroupId` INTEGER NOT NULL,
    `FieldId` INTEGER NOT NULL,
    `description` VARCHAR(191) NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    UNIQUE INDEX `Reservoir_name_key`(`name`),
    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- CreateTable
CREATE TABLE `Well` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(191) NOT NULL,
    `AssetGroupId` INTEGER NOT NULL,
    `FieldId` INTEGER NOT NULL,
    `description` VARCHAR(191) NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    UNIQUE INDEX `Well_name_key`(`name`),
    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- CreateTable
CREATE TABLE `AssetGroup` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(191) NOT NULL,
    `description` VARCHAR(191) NOT NULL,
    `createdAt` DATETIME(3) NOT NULL DEFAULT CURRENT_TIMESTAMP(3),
    `updatedAt` DATETIME(3) NOT NULL,

    UNIQUE INDEX `AssetGroup_name_key`(`name`),
    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
