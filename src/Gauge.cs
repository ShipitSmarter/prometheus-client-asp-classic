using System;
using SIS.PrometheusCOM.Contract;

namespace SIS.PrometheusCOM.Server;

internal class Gauge : Contract.IGauge
{
    private Prometheus.Gauge _gauge;

    public Gauge(Prometheus.Gauge gauge)
    { 
        _gauge = gauge;
    }

    double Contract.IGauge.Value => _gauge.Value;

    void Contract.IGauge.Inc()
    {
        _gauge.Inc();
    }

    void Contract.IGauge.Add(double increment)
    {
        _gauge.Inc(increment);
    }

    void IGauge.Set(double value)
    {
        _gauge.Set(value);
    }

    void IGauge.Dec()
    {
        _gauge.Dec();
    }

    void IGauge.Subract(double decrement)
    {
        _gauge.Dec(decrement);
    }

    IGaugeChild Contract.IGauge.WithLabels(object[] labelValues)
    {
        var child = _gauge.WithLabels(Array.ConvertAll(labelValues, x => x as string));
        return new GaugeChild(child);
    }
}

internal class GaugeChild : Contract.IGaugeChild
{
    private Prometheus.Gauge.Child _child;

    public GaugeChild(Prometheus.Gauge.Child child)
    {
        _child = child;
    }

    double IGaugeChild.Value => _child.Value;

    void IGaugeChild.Add(double increment)
    {
        _child.Inc(increment);
    }

    void IGaugeChild.Inc()
    {
        _child.Inc();
    }

    void IGaugeChild.Set(double value)
    {
        _child.Set(value);
    }

    void IGaugeChild.Dec()
    {
        _child.Dec();
    }

    void IGaugeChild.Subract(double decrement)
    {
        _child.Dec(decrement);
    }
}
