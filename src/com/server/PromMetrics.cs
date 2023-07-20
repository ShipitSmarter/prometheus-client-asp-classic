namespace SIS.PrometheusCOM.Server;

internal static class PromMetrics {
    static PromMetrics()
    {
        Prometheus.Metrics.SuppressDefaultMetrics();
    }

    public static Prometheus.CollectorRegistry DefaultRegistry => Prometheus.Metrics.DefaultRegistry;

    public static Prometheus.Counter CreateCounter(string name, string help) => 
        Prometheus.Metrics.CreateCounter(name, help, configuration: null);

    public static Prometheus.Counter CreateCounter(string name, string help, string[] labelNames) =>
        Prometheus.Metrics.CreateCounter(name, help, labelNames, configuration: null);
}