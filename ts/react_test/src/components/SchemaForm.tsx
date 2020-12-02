import * as React from "react";

import MuiForm from "@rjsf/material-ui";
import { JSONSchema7 } from "json-schema";

export class SchemaForm extends React.Component<{}, {}> {
    public render() {
        const schema: JSONSchema7 = {
            title: 'Todo',
            type: 'object',
            required: ['title'],
            properties: {
                title: { type: 'string', title: "Title", default: "A new task" },
                done: { type: 'boolean', title: "Done?", default: false },
                'fixed-length-list': {
                    type: 'array', items: [
                        { type: 'string', title: 'String1' },
                        { type: 'string', title: 'String2' },
                    ]
                },
                'list': {
                    type: 'array', items: { type: 'string' }
                },
            }
        };
        const log = (type: string) => console.log.bind(console, type);
        return (
            <MuiForm schema={schema}
                onChange={log("changed")}
                onSubmit={log("submitted")}
                onError={log("errors")} />
        );
    }
}
