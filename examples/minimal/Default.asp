<% ' Follows the Usage instruction from README.md %>

<!-- #include virtual = "/prometheus-client/init.inc" -->

<%
    ' =====================
    '   Collector Registry
    ' =====================
%>

<!-- #include virtual = "/prometheus-client/collector-registry.inc" -->

<%
Dim registry
Set registry = New prom_CollectorRegistry
registry.Prefix = "asp_" ' Optional
%>

<%
    ' =====================
    '   Counter collector
    ' =====================
%>

<!-- #include virtual = "/prometheus-client/counter.inc" -->

<%
Dim builder, counter
Set builder = New prom_CounterBuilder
builder().with_name("metric_name").with_help("A description about this metric")
Set counter = builder.register(registry)
%>

<%
    ' =====================
    '    Counter sample
    ' =====================
%>

<%
Dim sample
Set sample = counter.get_without_labels()
%>

<%
sample.inc
sample.add 3.254
%>

<%
    ' =====================
    '         Output
    ' =====================
%>

<!-- #include virtual = "/prometheus-client/bridges/prom-exp-fmt.inc" -->

<%
prom_write_prom_exp_fmt registry
%>
