using System.Runtime.InteropServices;

namespace SIS.PrometheusCOM.Contract;

[ComVisible(true)]
[Guid(ContractIds.Metrics.InterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface IMetrics
{
    ICollectorRegistry Registry { get; }

    /// <summary>
    /// Create a new unlabeled Counter.
    /// </summary>
    ICounter CreateCounter(string name, string help);

    /// <summary>
    /// Create a new labeled Counter.
    /// </summary>
    ICounter CreateLabeledCounter(string name, string help, object[] labelNames);
}
