using System.Runtime.InteropServices;

namespace SIS.PrometheusCOM.Contract;

[ComVisible(true)]
[Guid(ContractIds.MetricFactory.InterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface IMetricFactory
{
    /// <summary>
    /// Create a new unlabeld Counter.
    /// </summary>
    ICounter CreateCounter(string name, string help);

    /// <summary>
    /// Create a new labeled Counter.
    /// </summary>
    ICounter CreateLabeledCounter(string name, string help, object[] labelNames);
}
