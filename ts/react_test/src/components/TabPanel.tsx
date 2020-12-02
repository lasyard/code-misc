import * as React from "react";

import Box from "@material-ui/core/Box";

interface TabPanelProps {
    children?: React.ReactNode;
    value: any;
    index: any;
}

export class TabPanel extends React.Component<TabPanelProps, {}> {
    public constructor(props: TabPanelProps) {
        super(props);
    }

    public render() {
        return <Box
            role="tabpanel"
            hidden={this.props.value !== this.props.index}
        >
            {this.props.value === this.props.index
                && this.props.children}
        </Box>
    }
}
