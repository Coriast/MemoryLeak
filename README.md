### MemoryLeak

Repositório geral de projetos menores de C/C++


<!-- {
	// Place your snippets for sql here. Each snippet is defined under a snippet name and has a prefix, body and 
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the 
	// same ids are connected.
	// Example:
	// "Print to console": {
	// 	"prefix": "log",
	// 	"body": [
	// 		"console.log('$1');",
	// 		"$2"
	// 	],
	// 	"description": "Log output to console"
	// }

	"select PixOut by PixOutId": {
		"prefix": "sPixOutById",
		"body": [
			"select * from fb_servicesystem..PixOut p (nolock)",
			"where p.PixOutId = ",
			"option(maxdop 1);"
		],
		"description": "Select PixOut by PixOutId"
	},

	"Select Outputs by EntityId": {
		"prefix": "sOutputByEntityId",
		"body": [
			"select * from fb_integrationsystem..OperationOutput (nolock)",
			"where EntityId =",
			"option(maxdop 1);",
			"",
			"select ",
			"o.OutputId,",
			"o.PartnerId,",
			"m.Name,",
			"m.MethodId,",
			"o.Parameters,",
			"o.Result,",
			"o.IpAddress,",
			"o.CreationDate,",
			"o.UpdateDate,",
			"o.StatusCode,",
			"o.NSUId",
			"from fb_integrationsystem..[Output] o (nolock) ",
			"inner join fb_integrationsystem..Method m (nolock) on m.methodid = o.methodid",
			"where o.outputid in ()",
			"option(maxdop 1);",
		],
		"description": "Select Outputs by OutputId with OperationOutput"
	}
}

-->
