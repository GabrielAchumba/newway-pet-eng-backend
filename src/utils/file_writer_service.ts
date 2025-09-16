import { Injectable } from '@nestjs/common';
import { promises as fs } from 'fs';
import * as path from 'path';

@Injectable()
export class FileWriterService {
  //private readonly filePath = path.join(__dirname, '../../data.json');

  async writeToFile(data: any, fileName: string): Promise<void> {

    const projectRoot = process.cwd();
    const baseFolder = `/python/${fileName}`
    const filePath = path.join(projectRoot, baseFolder);

    try {
      // Convert object/array to pretty JSON
      const jsonData = JSON.stringify(data, null, 2);

      // Write file (overwrites if exists)
      await fs.writeFile(filePath, jsonData, 'utf-8');
      console.log('Data written successfully to data.json');
    } catch (error) {
      console.error('Error writing file:', error);
      throw error;
    }
  }

  async readFromFile(fileName: string): Promise<any> {

    const baseFolder = `/python/${fileName}`
    const filePath = path.join(__dirname, baseFolder);

    try {
      const rawData = await fs.readFile(filePath, 'utf-8');
      return JSON.parse(rawData);
    } catch (error) {
      if (error.code === 'ENOENT') {
        console.warn('File not found, returning empty object');
        return {};
      }
      throw error;
    }
  }
}