using System.Runtime.InteropServices;

namespace SIS.PrometheusCOM.Contract;

[ComVisible(true)]
[Guid(ContractIds.GaugeChild.InterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface IGaugeChild
{
    /// <summary>
    /// The value of this Gauge.
    /// </summary>
    double Value { get; }

    /// <summary>
    /// Increment the value of this Gauge by 1.
    /// </summary>
    void Inc();

    /// <summary>
    /// Add to the value of this Gauge.
    /// </summary>
    void Add(double increment);

    /// <summary>
    /// Set the value of this Gauge.
    /// </summary>
    void Set(double value);

    /// <summary>
    /// Decrement the value of this Gauge by 1.
    /// </summary>
    void Dec();

    /// <summary>
    /// Subract from the value of this Gauge.
    /// </summary>
    void Subract(double decrement);
}

[ComVisible(true)]
[Guid(ContractIds.Gauge.InterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface IGauge
{
    /// <summary>
    /// The value of this Gauge.
    /// </summary>
    double Value { get; }

    /// <summary>
    /// Increment the value of this Gauge by 1.
    /// </summary>
    void Inc();

    /// <summary>
    /// Add to the value of this Gauge.
    /// </summary>
    void Add(double increment);

    /// <summary>
    /// Set the value of this Gauge.
    /// </summary>
    void Set(double value);

    /// <summary>
    /// Decrement the value of this Gauge by 1.
    /// </summary>
    void Dec();

    /// <summary>
    /// Subract from the value of this Gauge.
    /// </summary>
    void Subract(double decrement);

    /// <summary>
    /// Get a Gauge with the specified label values.
    /// </summary>
    IGaugeChild WithLabels(object[] labelValues);
}