using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QtTestResultsCleaner
{
    class Program
    {
        private static PartFilePathGenerator filePathsGenerator;
        static void Main(string[] args)
        {
            if(args.Length != 1)
            {
                throw new ArgumentException("Program must be provided with a filepath argument.");
            }
            string filePath = args[0];
            if (!File.Exists(filePath))
            {
                throw new ArgumentException($"File '{filePath}' doesn't exist.");
            }
            filePathsGenerator = new PartFilePathGenerator(filePath);

            string[] textContents = File.ReadAllLines(filePath);

            SplitIntoCleanedUpFiles(textContents, filePath);
            File.Delete(filePath);
        }

        private static void SplitIntoCleanedUpFiles(IReadOnlyList<string> originalFileContents, string filePath)
        {
            var fileContents = new List<string>();
            foreach(string line in originalFileContents)
            {
                if (line.StartsWith("<?xml") && fileContents.Any())
                {
                    File.WriteAllLines(filePathsGenerator.GetNewPartFilePath(), fileContents);
                    fileContents.Clear();
                }
                fileContents.Add(line);
            }
            File.WriteAllLines(filePathsGenerator.GetNewPartFilePath(), fileContents);
        }
    }
}
