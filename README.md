# prometheus-client-asp-classic

An ASP Classic library to setup and collect metrics from your application and make them availble in the Prometheus Exposition Format.

## Usage

> Wherever you use the library, you will need to include [`init.inc`](src/init.inc) to include all required internal files.

First create a new `CollectorRegistry` that will keep track of all the collectors:

```vbscript
<!-- #include virtual = "/prometheus-client/init.inc" -->
<!-- #include virtual = "/prometheus-client/collector-registry.inc" -->

<%
Dim registry
Set registry = New prom_CollectorRegistry
registry.Prefix = "asp_" ' Optional
%>
```

Now create a new `Collector` for a metric, e.g. `Counter`, and register it to `registry` using one of the builders:

```vbscript
<!-- #include virtual = "/prometheus-client/counter.inc" -->

<%
Dim builder, counter
Set builder = New prom_CounterBuilder
builder().with_name("metric_name").with_help("A description about this metric")
Set counter = builder.register(registry)
%>
```

With the counter ready you can request a sample using `get_for_labels()` or `get_without_labels()`, depending on if labels were set using `with_label_names` on the builder:

```vbscript
<%
Dim sample
Set sample = counter.get_without_labels()
%>
```

The counter can be incremented or added to with the `inc` or `add` methods:

```vbscript
<%
sample.inc
sample.add 3.254
%>
```

To output all the registerd collectors in the Prometheus Exposition Format, call `prom_write_prom_exp_fmt`:

```vbscript
<!-- #include virtual = "/prometheus-client/bridges/prom-exp-fmt.inc" -->

<%
prom_write_prom_exp_fmt registry
%>
```
