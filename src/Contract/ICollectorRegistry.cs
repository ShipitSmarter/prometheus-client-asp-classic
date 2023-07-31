using System.Runtime.InteropServices;

namespace SIS.PrometheusCOM.Contract;

[ComVisible(true)]
[Guid(ContractIds.CollectorRegistry.InterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface ICollectorRegistry
{
    /// <summary>
    /// Collect all metrics and export them in text document format.
    /// </summary>
    string CollectAndExportAsText();
}
