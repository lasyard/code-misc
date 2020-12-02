import * as React from "react";

import AppBar from "@material-ui/core/AppBar";
import Typography from "@material-ui/core/Typography";
import Toolbar from "@material-ui/core/Toolbar";

interface HelloProps {
    compiler: string;
    framework: string;
}

export class Title extends React.Component<HelloProps, {}> {
    render() {
        return (
            <React.Fragment>
                <AppBar>
                    <Typography>Hello from {this.props.compiler} and {this.props.framework}!</Typography>
                </AppBar>
                <Toolbar />
            </React.Fragment>
        );
    }
}
