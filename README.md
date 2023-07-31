# prometheus-client-asp-classic

An COM library wrapping around [prometheus-net](https://github.com/prometheus-net/prometheus-net) to collect and expose Prometheus in ASP Classic.

## Usage

To use this library you will need to create the one object that is used to interact with everything in the library: `SIS.PrometheusCOM.Metrics`.  
It is posssible to just create this object inside your ASP code for a minimal setup, but it is recommended to register the object in your `Global.asa` to only create the object once and have easy access to it in all your pages.

### Global.asa (Recommended)

First register the object to the `application` scope and choose an id for it, in this case `Metrics`:

```html
<object runat="server" scope="application" id="Metrics" progid="SIS.PrometheusCOM.Metrics">
</object>
```

Now you can access this object from anywhere in your ASP code like so:

```vbscript
Sub do_something
    Dim counter: Set counter = Metrics.CreateCounter("asp_some_counter_total", "Total of some_counter")
    counter.Inc()
End Sub
```

To create a metrics endpoint that Prometheus can scrape, create a new file (e.g. `metrics.asp`) and add the following ASP code to set the response correctly:

```vbscript
<%
    Response.CodePage = 65001
    Response.Charset = "utf-8"
    Response.ContentType = "text/plain; version=0.0.4"
    Response.Write Metrics.Registry.CollectAndExportAsText()
%>
```

Check [examples/global](examples/global) for a full example using the `Global.asa` file.

### Minimal

For the minimal approach you just have to create the metrics object yourself like so:

```vbscript
<%
    Dim metrics: Set metrics = Server.CreateObject("SIS.PrometheusCOM.Metrics")
%>
```

You can than use `metrics` to interact with the library, e.g. calling `metrics.CreateCounter(...)`.

Check [examples/minimal](examples/minimal) for a more elaborate example.
