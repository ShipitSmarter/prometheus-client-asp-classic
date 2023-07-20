using System.IO;

namespace SIS.PrometheusCOM.Server;

internal class CollectorRegistry : Contract.ICollectorRegistry
{
    string Contract.ICollectorRegistry.CollectAndExportAsText()
    {
        using MemoryStream stream = new();
        PromMetrics.DefaultRegistry.CollectAndExportAsTextAsync(stream).Wait();
        stream.Seek(0, SeekOrigin.Begin);
        using StreamReader reader = new(stream);
        return reader.ReadToEnd();
    }
}
