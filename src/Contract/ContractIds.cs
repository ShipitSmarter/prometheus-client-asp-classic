namespace SIS.PrometheusCOM.Contract;

public sealed class ContractIds
{
    public sealed class Metrics {
        public const string InterfaceId = "73346b99-e4c1-49b5-b318-7e353c31911e";
        public const string ClassId = "4e76ea0c-bff1-45cd-9e3f-056eb01f957b";
        public const string ProgId = "SIS.PrometheusCOM.Metrics";
    }

    public sealed class CollectorRegistry {
        public const string InterfaceId = "4630da37-e539-44fa-8cba-698b8be03134";
    }

    public sealed class Counter {
        public const string InterfaceId = "eadd9784-c935-467d-815b-0e39e0a00834";
    }

    public sealed class CounterChild {
        public const string InterfaceId = "09089077-5b04-4c83-bcd7-044af8819835";
    }

    public sealed class Gauge {
        public const string InterfaceId = "622b16fc-54b6-4212-94c3-42043709dad5";
    }

    public sealed class GaugeChild {
        public const string InterfaceId = "b8bfe0a5-3651-4deb-8238-8b6f3c69e51a";
    }
}
