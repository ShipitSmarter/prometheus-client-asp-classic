using System;
using System.Runtime.InteropServices;
using SIS.PrometheusCOM.Contract;

namespace SIS.PrometheusCOM.Server;

[ComVisible(true)]
[Guid(ContractIds.Metrics.ClassId)]
[ProgId(ContractIds.Metrics.ProgId)]
[ClassInterface(ClassInterfaceType.None)]
public class Metrics : Contract.IMetrics
{
    private readonly ICollectorRegistry _registry = new CollectorRegistry();

    ICollectorRegistry IMetrics.Registry => _registry;

    ICounter IMetrics.CreateCounter(string name, string help)
    {
        var counter = PromMetrics.CreateCounter(name, help);
        return new Counter(counter);
    }

    ICounter IMetrics.CreateLabeledCounter(string name, string help, object[] labelNames)
    {
        var counter = PromMetrics.CreateCounter(name, help, Array.ConvertAll(labelNames, x => x as string));
        return new Counter(counter);
    }
}
