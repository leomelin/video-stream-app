import koa from 'koa'; // koa@2
import cors from 'koa-cors';
import koaRouter from 'koa-router'; // koa-router@next
import koaBody from 'koa-bodyparser'; // koa-bodyparser@next
import { graphqlKoa, graphiqlKoa } from 'apollo-server-koa';
import schema from './schema';

const app = new koa();
const router = new koaRouter();
const PORT = 4000;
app.use(cors());

// koaBody is needed just for POST.
router.post('/graphql', koaBody(), graphqlKoa({ schema }));
router.get('/graphql', graphqlKoa({ schema }));

router.get('/graphiql', graphiqlKoa({ endpointURL: '/graphql' }));

app.use(router.routes());
app.use(router.allowedMethods());
app.listen(PORT);
