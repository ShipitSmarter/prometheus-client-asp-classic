using System.Runtime.InteropServices;

namespace COM.Contract;

[ComVisible(true)]
[Guid(ContractIds.ServerInterfaceId)]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface IServer
{
    /// <summary>
    /// Compute the value of the constant Pi.
    /// </summary>
    double ComputePi();
}