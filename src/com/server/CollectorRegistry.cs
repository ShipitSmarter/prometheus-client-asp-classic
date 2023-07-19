using System.IO;
using System.Runtime.InteropServices;
using SIS.PrometheusCOM.Contract;

namespace SIS.PrometheusCOM.Server;

[ComVisible(true)]
[Guid(ContractIds.CollectorRegistry.ClassId)]
[ProgId(ContractIds.CollectorRegistry.ProgId)]
[ClassInterface(ClassInterfaceType.None)]
public class CollectorRegistry : Contract.ICollectorRegistry
{
    string Contract.ICollectorRegistry.CollectAndExportAsText()
    {
        using MemoryStream stream = new();
        Metrics.DefaultRegistry.CollectAndExportAsTextAsync(stream).Wait();
        stream.Seek(0, SeekOrigin.Begin);
        using StreamReader reader = new(stream);
        return reader.ReadToEnd();
    }
}
