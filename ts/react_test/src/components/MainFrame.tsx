import * as React from "react";

import { Title } from "./Title";
import { MuiButtons } from "./MuiButtons";
import { TabPanel } from "./TabPanel";
import { SchemaForm } from "./SchemaForm";

import { autobind } from "core-decorators";
import Container from "@material-ui/core/Container";
import Tabs from "@material-ui/core/Tabs";
import Tab from "@material-ui/core/Tab";

interface MainFrameState {
    tabValue: any;
}

export class MainFrame extends React.Component<{}, MainFrameState> {
    public constructor(props: {}) {
        super(props);
        this.state = { tabValue: 0 };
    }

    @autobind
    private handleTabsChange(_event: React.ChangeEvent<{}>, value: any): void {
        this.setState({ tabValue: value });
    }

    public render() {
        return (
            <Container disableGutters>
                <Title
                    compiler="TypeScript"
                    framework="React"
                />
                <Tabs value={this.state.tabValue} onChange={this.handleTabsChange}>
                    <Tab label="Buttons"></Tab>
                    <Tab label="SchemaForm"></Tab>
                    <Tab label="Nothing"></Tab>
                </Tabs>
                <TabPanel value={this.state.tabValue} index={0}>
                    <MuiButtons />
                </TabPanel>
                <TabPanel value={this.state.tabValue} index={1}>
                    <SchemaForm />
                </TabPanel>
            </Container>
        );
    }
}
