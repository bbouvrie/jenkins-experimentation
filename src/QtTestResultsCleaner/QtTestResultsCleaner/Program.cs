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

            string[] textContents = File.ReadAllLines(filePath);

            IList<string> newTextContents = TrimSuperfluousXmlTags(textContents);

            File.WriteAllLines(filePath, newTextContents);
        }

        private static IList<string> TrimSuperfluousXmlTags(IReadOnlyList<string> lines)
        {
            var newTextContents = new List<string>();
            newTextContents.Add(lines[0]); // Expected to be an <?xml tag
            // Remove subsequent <?xml tags :
            newTextContents.AddRange(lines.Where(line => !line.StartsWith("<?xml")));
            return newTextContents;
        }
    }
}
