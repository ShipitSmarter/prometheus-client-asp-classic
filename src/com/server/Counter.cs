using System;
using SIS.PrometheusCOM.Contract;

namespace SIS.PrometheusCOM.Server;

internal class Counter : Contract.ICounter
{
    private Prometheus.Counter _counter;

    public Counter(Prometheus.Counter counter)
    { 
        _counter = counter;
    }

    double Contract.ICounter.Value => _counter.Value;

    void Contract.ICounter.Add(double increment)
    {
        _counter.Inc(increment);
    }

    void Contract.ICounter.Inc()
    {
        _counter.Inc();
    }

    ICounterChild Contract.ICounter.WithLabels(object[] labelValues)
    {
        var child = _counter.WithLabels(Array.ConvertAll(labelValues, x => x as string));
        return new CounterChild(child);
    }
}

internal class CounterChild : Contract.ICounterChild
{
    private Prometheus.Counter.Child _child;

    public CounterChild(Prometheus.Counter.Child child)
    {
        _child = child;
    }

    double ICounterChild.Value => _child.Value;

    void ICounterChild.Add(double increment)
    {
        _child.Inc(increment);
    }

    void ICounterChild.Inc()
    {
        _child.Inc();
    }
}
