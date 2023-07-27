using System;
using System.Runtime.InteropServices;
using SIS.PrometheusCOM.Contract;

namespace SIS.PrometheusCOM.Server;

[ComVisible(true)]
[Guid(ContractIds.Metrics.ClassId)]
[ProgId(ContractIds.Metrics.ProgId)]
[ClassInterface(ClassInterfaceType.None)]
public class MetricsCOM : Contract.IMetrics
{
    ICollectorRegistry IMetrics.Registry => Metrics.Registry;
    ICounter IMetrics.CreateCounter(string name, string help) => Metrics.CreateCounter(name, help);
    ICounter IMetrics.CreateLabeledCounter(string name, string help, object[] labelNames) => Metrics.CreateLabeledCounter(name, help, labelNames);
}

internal static class Metrics
{
    static Metrics()
    {
        Prometheus.Metrics.SuppressDefaultMetrics();
        Registry = new CollectorRegistry();
    }

    internal static Prometheus.CollectorRegistry PromRegistry => Prometheus.Metrics.DefaultRegistry;
    public static ICollectorRegistry Registry { get; }

    public static ICounter CreateCounter(string name, string help)
    {
        var counter = Prometheus.Metrics.CreateCounter(name, help);
        return new Counter(counter);
    }

    public static ICounter CreateLabeledCounter(string name, string help, object[] labelNames)
    {
        var counter = Prometheus.Metrics.CreateCounter(name, help, Array.ConvertAll(labelNames, x => x as string));
        return new Counter(counter);
    }
}
