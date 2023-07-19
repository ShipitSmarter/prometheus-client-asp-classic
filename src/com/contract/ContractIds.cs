namespace SIS.PrometheusCOM.Contract;

public sealed class ContractIds
{
    public sealed class MetricFactory {
        public const string InterfaceId = "73346b99-e4c1-49b5-b318-7e353c31911e";
        public const string ClassId = "4e76ea0c-bff1-45cd-9e3f-056eb01f957b";
        public const string ProgId = "SIS.PrometheusCOM.MetricFactory";
    }

    public sealed class CollectorRegistry {
        public const string InterfaceId = "4630da37-e539-44fa-8cba-698b8be03134";
        public const string ClassId = "89de96fb-fcf9-4231-97fe-d5814160d090";
        public const string ProgId = "SIS.PrometheusCOM.CollectorRegistry";
    }

    public sealed class Counter {
        public const string InterfaceId = "eadd9784-c935-467d-815b-0e39e0a00834";
        public const string ClassId = "215dc82e-df70-4482-87dc-73ef4ebf68ca";
        public const string ProgId = "SIS.PrometheusCOM.Counter";
    }

    public sealed class CounterChild {
        public const string InterfaceId = "09089077-5b04-4c83-bcd7-044af8819835";
        public const string ClassId = "59832c22-83a0-41b0-9495-801898b51264";
        public const string ProgId = "SIS.PrometheusCOM.CounterChild";
    }
}
