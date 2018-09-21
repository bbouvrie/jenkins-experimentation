using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QtTestResultsCleaner
{
    internal class PartFilePathGenerator
    {
        private readonly string fileName;
        private readonly string extension;
        private readonly string directory;
        private int currentPartNumber = 0;

        public PartFilePathGenerator(string originalFilePath)
        {
            fileName = Path.GetFileNameWithoutExtension(originalFilePath);
            extension = Path.GetExtension(originalFilePath);
            directory = Path.GetDirectoryName(originalFilePath);
        }

        public string GetNewPartFilePath()
        {
            string partName = $"_{currentPartNumber++}";
            return Path.Combine(directory, $"{fileName}_{currentPartNumber}{extension}");
        }
    }
}
