<a name="database_methods"></a>
# Database Methods

`db._document( document)`

This method finds a document given its identifier. It returns the document. Note that the returned document contains some pseudo-attributes, namely _id, _key, and _rev. _id and _key contain the document handle and key, and _rev contains the revision of the document.

An error is thrown if the _rev does not longer match the current revision of the document.

`db._document( document-handle)`

As before. Instead of document a document-handle can be passed as first argument.

*Examples*

Returns the document:

	arango> db._document("example/3053939");
	{ "_id" : "example/3053939", "_key" : "3053939", "_rev" : "3053939", "Hello" : "World" }

`db._exists( document)`

This method determines whether a document exists given its identifier. Instead of returning the found document or an error, this method will return either true or false. It can thus be used for easy existence checks.

No error will be thrown if the sought document or collection does not exist. Still this method will throw an error if used improperly, e.g. when called with a non-document handle.

`db._exists( document-handle)`

`db._replace( document, data)`

The method returns a document with the attributes _id, _rev and _oldRev. The attribute _id contains the document handle of the updated document, the attribute _rev contains the document revision of the updated document, the attribute _oldRev contains the revision of the old (now replaced) document.

If there is a conflict, i. e. if the revision of the document does not match the revision in the collection, then an error is thrown.

`db._replace( document, data, true)`

As before, but in case of a conflict, the conflict is ignored and the old document is overwritten.

`db._replace( document, data, true, waitForSync)`

The optional waitForSync parameter can be used to force synchronisation of the document replacement operation to disk even in case that the waitForSync flag had been disabled for the entire collection. Thus, the waitForSync parameter can be used to force synchronisation of just specific operations. To use this, set the waitForSync parameter to true. If the waitForSync parameter is not specified or set to false, then the collection's default waitForSync behavior is applied. The waitForSync parameter cannot be used to disable synchronisation for collections that have a default waitForSync value of true.

`db._replace( document-handle, data)`

As before. Instead of document a document-handle can be passed as first argument.

*Examples*

Create and replace a document:

	arango> a1 = db.example.save({ a : 1 });
	{ "_id" : "example/1717678", "_key" : "1717678", "_rev" : "1717678" }
	arango> a2 = db._replace(a1, { a : 2 });
	{ "_id" : "example/1717678", "_key" : "1717678", "_rev" : "1783214", "_oldRev" : "1717678" }
	arango> a3 = db._replace(a1, { a : 3 });
	JavaScript exception in file '(arango)' at 1,9: [ArangoError 1200: conflict: cannot replace document]
	!a3 = db._replace(a1, { a : 3 });
	!        ^
	arango> a4 = db.example.replace(a1, { a : 4 }, true);
	{ "_id" : "example/1717678", "_key" : "1717678", "_rev" : "1848750", "_oldRev" : "1783214" }

`db._update( document, data, overwrite, keepNull, waitForSync)`

Updates an existing document. The document must be a document in the current collection. This document is then patched with the data given as second argument. The optional overwrite parameter can be used to control the behavior in case of version conflicts (see below). The optional keepNull parameter can be used to modify the behavior when handling null values. Normally, null values are stored in the database. By setting the keepNull parameter to false, this behavior can be changed so that all attributes in data with null values will be removed from the target document.

The optional waitForSync parameter can be used to force synchronisation of the document update operation to disk even in case that the waitForSync flag had been disabled for the entire collection. Thus, the waitForSync parameter can be used to force synchronisation of just specific operations. To use this, set the waitForSync parameter to true. If the waitForSync parameter is not specified or set to false, then the collection's default waitForSync behavior is applied. The waitForSync parameter cannot be used to disable synchronisation for collections that have a default waitForSync value of true.

The method returns a document with the attributes _id, _rev and _oldRev. The attribute _id contains the document handle of the updated document, the attribute _rev contains the document revision of the updated document, the attribute _oldRev contains the revision of the old (now replaced) document.

If there is a conflict, i. e. if the revision of the document does not match the revision in the collection, then an error is thrown.

`db._update( document, data, true)`

As before, but in case of a conflict, the conflict is ignored and the old document is overwritten.

`db._update( document-handle, data)`

As before. Instead of document a document-handle can be passed as first argument.

*Examples*

Create and update a document:

	arango> a1 = db.example.save({ a : 1 });
	{ "error" : false, "_id" : "example/19660691", "_key" : "19660691", "_rev" : "19660691" }
	arango> a2 = db._update(a1, { b : 2 });
	{ "error" : false, "_id" : "example/19660691", "_key" : "19660691", "_rev" : "19791763" }
	arango> a3 = db._update(a1, { c : 3 });
	JavaScript exception in file 'client/client.js' at 2364,13: [ArangoError 1200: precondition failed]
	!      throw new ArangoError(requestResult);
	!            ^
	arango> a4 = db.example.update(a1, { c : 3 }, true);
	{ "error" : false, "_id" : "example/19660691", "_key" : "19660691", "_rev" : "19857299" }

`db._remove( document)`

Removes a document. If there is revision mismatch, then an error is thrown.

`db._remove( document, true)`

Removes a document. If there is revision mismatch, then mismatch is ignored and document is deleted. The function returns true if the document existed and was deleted. It returns false, if the document was already deleted.

`db._remove( document, true, waitForSync)`

The optional waitForSync parameter can be used to force synchronisation of the document deletion operation to disk even in case that the waitForSync flag had been disabled for the entire collection. Thus, the waitForSync parameter can be used to force synchronisation of just specific operations. To use this, set the waitForSync parameter to true. If the waitForSync parameter is not specified or set to false, then the collection's default waitForSync behavior is applied. The waitForSync parameter cannot be used to disable synchronisation for collections that have a default waitForSync value of true.

`db._remove( document-handle, data)`

As before. Instead of document a document-handle can be passed as first argument.

*Examples*

Remove a document:

	arango> a1 = db.example.save({ a : 1 });
	{ "_id" : "116308/4214943", "_rev" : "4214943" }
	arango> db._remove(a1);
	true
	arango> db._remove(a1);
	JavaScript exception in file '(arango)' at 1,4: [ArangoError 1202: document not found: cannot remove document]
	!db._remove(a1);
	! ^
	arango> db._remove(a1, true);
	false

Remove a document with a conflict:

	arango> a1 = db.example.save({ a : 1 });
	{ "_id" : "116308/4042634", "_rev" : "4042634" }
	arango> a2 = db._replace(a1, { a : 2 });
	{ "_id" : "116308/4042634", "_rev" : "4108170", "_oldRev" : 4042634 }
	arango> db._delete(a1);
	JavaScript exception in file '(arango)' at 1,4: [ArangoError 1200: conflict: cannot delete document]
	!db._delete(a1);
	! ^
	arango> db._delete(a1, true);
	true
	arango> db._document(a1);
	JavaScript exception in file '(arango)' at 1,4: [ArangoError 1202: document not found: document not found]
	!db._document(a1);
	! ^

<!--
@anchor HandlingDocumentsDbRead
@copydetails JS_DocumentVocbase

@CLEARPAGE
@anchor HandlingDocumentsDbExists
@copydetails JS_ExistsVocbase

@CLEARPAGE
@anchor HandlingDocumentsDbReplace
@copydetails JS_ReplaceVocbase

@CLEARPAGE
@anchor HandlingDocumentsDbUpdate
@copydetails JS_UpdateVocbase

@CLEARPAGE
@anchor HandlingDocumentsDbRemove
@copydetails JS_RemoveVocbase

@BNAVIGATE_HandlingDocuments
-->