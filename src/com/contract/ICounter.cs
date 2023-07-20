using System.Runtime.InteropServices;

namespace SIS.PrometheusCOM.Contract;

[ComVisible(true)]
[Guid(ContractIds.CounterChild.InterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface ICounterChild
{
    /// <summary>
    /// The value of this Counter.
    /// </summary>
    double Value { get; }

    /// <summary>
    /// Increment the value of this Counter by 1.
    /// </summary>
    void Inc();

    /// <summary>
    /// Add to the value of this Counter.
    /// </summary>
    void Add(double increment);
}

[ComVisible(true)]
[Guid(ContractIds.Counter.InterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface ICounter
{
    /// <summary>
    /// The value of this Counter.
    /// </summary>
    double Value { get; }

    /// <summary>
    /// Increment the value of this Counter by 1.
    /// </summary>
    void Inc();

    /// <summary>
    /// Add to the value of this Counter.
    /// </summary>
    void Add(double increment);

    /// <summary>
    /// Get a Counter with the specified label values.
    /// </summary>
    ICounterChild WithLabels(object[] labelValues);
}
