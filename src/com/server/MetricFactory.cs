using System;
using System.Runtime.InteropServices;
using SIS.PrometheusCOM.Contract;

namespace SIS.PrometheusCOM.Server;

[ComVisible(true)]
[Guid(ContractIds.MetricFactory.ClassId)]
[ProgId(ContractIds.MetricFactory.ProgId)]
[ClassInterface(ClassInterfaceType.None)]
public class MetricFactory : Contract.IMetricFactory
{
    public Contract.ICounter CreateCounter(string name, string help)
    {
        var counter = Metrics.CreateCounter(name, help);
        return new Counter(counter);
    }

    public Contract.ICounter CreateLabeledCounter(
        string name, string help, object[] labelNames)
    {
        var counter = Metrics.CreateCounter(name, help, Array.ConvertAll(labelNames, x => x as string));
        return new Counter(counter);
    }
}
