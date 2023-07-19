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

    int TestObjectParam([MarshalAs(UnmanagedType.Struct)]ITest test);
}

[ComVisible(true)]
[Guid("f23417fb-1b08-4a42-beff-0406bc9e4d1a")]
[InterfaceType(ComInterfaceType.InterfaceIsDual)]
public interface ITest
{
    int SomeProperty { get; set; }
}
