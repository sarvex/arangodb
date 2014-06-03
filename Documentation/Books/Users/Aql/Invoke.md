<a name="how_to_invoke_aql"></a>
# How to invoke AQL

You can run AQL queries from your application via the HTTP REST API. The full
API description is available at [Http Interface for AQL Query Cursor](../HttpAqlQueryCursor/README.md). 

You can also run AQL queries from arangosh. To do so, first create an
ArangoStatement object as follows:

    arangosh> stmt = db._createStatement( { "query": "FOR i IN [ 1, 2 ] RETURN i * 2" } );
    [object ArangoStatement]

To execute the query, use the `execute` method:

    arangosh> c = stmt.execute();
    [object ArangoQueryCursor]

This has executed the query. The query results are available in a cursor
now. The cursor can return all its results at once using the `toArray` method.
This is a short-cut that you can use if you want to access the full result
set without iterating over it yourself.

    arangosh> c.toArray();
    [2, 4]
    
Cursors can also be used to iterate over the result set document-by-document.
To do so, use the `hasNext` and `next` methods of the cursor:

    arangosh> while (c.hasNext()) { require("internal").print(c.next()); }
    2
    4

Please note that you can iterate over the results of a cursor only once, and that
the cursor will be empty when you have fully iterated over it. To iterate over
the results again, the query needs to be re-executed.
 
Additionally, the iteration can be done in a forward-only fashion. There is no 
backwards iteration or random access to elements in a cursor.    

To execute an AQL query using bind parameters, you need to create a statement first
and then bind the parameters to it before execution:

    arangosh> stmt = db._createStatement( { "query": "FOR i IN [ @one, @two ] RETURN i * 2" } );
    [object ArangoStatement]
    arangosh> stmt.bind("one", 1);
    arangosh> stmt.bind("two", 2);
    arangosh> c = stmt.execute();
    [object ArangoQueryCursor]

The cursor results can then be dumped or iterated over as usual, e.g.:
    
    arangosh> c.toArray();
    [2, 4]

or 

    arangosh> while (c.hasNext()) { require("internal").print(c.next()); }
    2
    4

Please note that bind variables can also be passed into the `_createStatement` method directly,
making it a bit more convenient:
    
    arangosh> stmt = db._createStatement( { 
      "query": "FOR i IN [ @one, @two ] RETURN i * 2", 
      "bindVars": { 
        "one": 1, 
        "two": 2 
      } 
    } );

Cursors also optionally provide the total number of results. By default, they do not. 
To make the server return the total number of results, you may set the `count` attribute to 
`true` when creating a statement:
    
    arangosh> stmt = db._createStatement( { "query": "FOR i IN [ 1, 2, 3, 4 ] RETURN i", "count": true } );

After executing this query, you can use the `count` method of the cursor to get the 
number of total results from the result set:
    
    arangosh> c = stmt.execute();
    [object ArangoQueryCursor]
    arangosh> c.count();
    4

Please note that the `count` method returns nothing if you did not specify the `count`
attribute when creating the query. 

This is intentional so that the server may apply optimizations when executing the query and 
construct the result set incrementally. Incremental creating of the result sets would not be possible
if the total number of results needs to be shipped to the client anyway. Therefore, the client
has the choice to specify `count` and retrieve the total number of results for a query (and
disable potential incremental result set creation on the server), or to not retrieve the total
number of results and allow the server to apply optimizations.

Please note that at the moment the server will always create the full result set for each query so 
specifying or omitting the `count` attribute currently does not have any impact on query execution.
This might change in the future. Future versions of ArangoDB might create result sets incrementally 
on the server-side and might be able to apply optimizations if a result set is not fully fetched by 
a client.